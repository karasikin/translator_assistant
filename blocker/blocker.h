#ifndef BLOCKER_H
#define BLOCKER_H

#include <functional>
#include <string>
#include <semaphore.h>
#include <signal.h>

class Blocker {
public:
    Blocker(const std::string &unique_name);
    ~Blocker();

    void setCollback(std::function<void()> collback);

    bool isThisProcessFirst() const;
    pid_t firstProcessPid() const;

private:
    void createOrOpenSemaphore();
    void createOrOpenShm();
    void initSignalHandling();

    static void quitSignalHandler(int id);
    static void nonFirstProcessSignalHandler(int id);

private:
    static const std::string semPostfix;
    static const std::string shmPostfix;

    static std::string uniqueItemsName;
    static std::function<void()> collback;

    sem_t *sem;
    int shm;
    pid_t *shm_ptr;

    bool isIFirst;

    struct sigaction quitSigaction;
    struct sigaction nonFirstProcessSigaction;
};

#endif // BLOCKER_H
