#include "SessionManager.h"

Preferences preferences;

SessionManager::SessionManager() {
    sessionId = preferences.getUInt("sessionId", 0);
    incrementSessionId();
    preferences.putUInt("sessionId", sessionId);
}

unsigned int SessionManager::getSessionId() {
    return sessionId;
}

void SessionManager::incrementSessionId() {
    sessionId++;
}