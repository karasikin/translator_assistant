#include "blocker.h"

#include <system_error>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

const std::string Blocker::semPostfix{"_sem"};
const std::string Blocker::shmPostfix{"shm"};

std::string Blocker::uniqueItemsName{"/default_blocking_items_name"};
std::function<void()> Blocker::collback = nullptr;

Blocker::Blocker(const std::string &unique_name)
    : isIFirst(true),
      quitSigaction(),
      nonFirstProcessSigaction()
{
    uniqueItemsName = "/" + unique_name;

    initSignalHandling();

    createOrOpenSemaphore();
    createOrOpenShm();

    if(isIFirst) {
        *shm_ptr = getpid();
    } else {
        kill(firstProcessPid(), SIGUSR1);
    }
}

Blocker::~Blocker() {
    sem_close(sem);
    munmap((void *)shm_ptr, sizeof(pid_t));
    close(shm);

    if(isIFirst) {
        sem_unlink((uniqueItemsName + semPostfix).c_str());
        shm_unlink((uniqueItemsName + shmPostfix).c_str());
    }
}

void Blocker::setCollback(std::function<void ()> collback) {
    this->collback = collback;
}

bool Blocker::isThisProcessFirst() const {
    return isIFirst;
}

pid_t Blocker::firstProcessPid() const {
    sem_wait(sem);
    auto pid = *shm_ptr;
    sem_post(sem);

    return pid;
}

void Blocker::createOrOpenSemaphore() {
    sem = sem_open((uniqueItemsName + semPostfix).c_str(), O_CREAT, 0777, 1);
    if(sem == SEM_FAILED) {
        throw std::system_error({}, "Failed semaphore creation.");
    }
}

void Blocker::createOrOpenShm() {
    sem_wait(sem);

    std::string shmName = uniqueItemsName + shmPostfix;

    shm = shm_open(shmName.c_str(), O_CREAT | O_EXCL | O_RDWR, 0777);
    if(shm < 0) {
        isIFirst = false;
    }

    if(isIFirst) {
        if(ftruncate(shm, sizeof(pid_t)) < 0) {
            throw std::system_error({}, "Failed shm truncate.");
        }
    } else {
        shm = shm_open(shmName.c_str(), O_RDWR, 0777);
    }

    auto addr = mmap(0, sizeof(pid_t), PROT_WRITE | PROT_READ, MAP_SHARED, shm, 0);

    if(addr == (char *)-1) {
        throw std::system_error({}, "Shm mmap failed.");
    }

    shm_ptr = (pid_t *)addr;

    sem_post(sem);
}

void Blocker::initSignalHandling() {
    quitSigaction.sa_handler = Blocker::quitSignalHandler;

    sigaction(SIGHUP, &quitSigaction, 0);
    sigaction(SIGINT, &quitSigaction, 0);
    sigaction(SIGQUIT, &quitSigaction, 0);
    sigaction(SIGTERM, &quitSigaction, 0);

    nonFirstProcessSigaction.sa_handler = Blocker::nonFirstProcessSignalHandler;

    sigaction(SIGUSR1, &nonFirstProcessSigaction, 0);
}

void Blocker::quitSignalHandler(int id) {
    if(id == SIGHUP ||
            id == SIGINT ||
            id == SIGQUIT ||
            id == SIGTERM)
    {
        sem_unlink((uniqueItemsName + semPostfix).c_str());
        shm_unlink((uniqueItemsName + shmPostfix).c_str());

        exit(0);
    }
}

void Blocker::nonFirstProcessSignalHandler(int id) {
    if(collback != nullptr && id == SIGUSR1) {
        collback();
    }
}
