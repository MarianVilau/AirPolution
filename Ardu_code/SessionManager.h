#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <Preferences.h>

class SessionManager {
public:
    SessionManager();
    unsigned int getSessionId();
private:
    unsigned int sessionId;
    void incrementSessionId();
};

#endif