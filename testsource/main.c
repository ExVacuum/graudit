/* ===========================================================
   Filename:main.c
   Project:Assignment 3: The Hoochamacallit System
   Name:Patrick Cho, Silas Bartha
   Date:02/15/2022
   Description: The data creator sends status messages at
                random intervals to a message queue
                established by the Data Reader (DR) program. 
   =========================================================== */

#include "../inc/dataCreator.h"

int main(int argc, char** argv) {
        
    // Get message queue ID
    int queueID = initMsgQ();
    
    // Once message queue established, send initial OK message
    sendMessage(queueID, DC_EVERYTHING_IS_OKAY);

    srandom(time(NULL));

    int status = 0;
    while(1) {
        // Sleep for a random amount of time within the allowed range
        sleep((random() % (SLEEP_MAX - SLEEP_MIN)) + SLEEP_MIN);
        
        // Randomly select a status code to send
        DCCode code = random() % (DC_MACHINE_IS_OFFLINE + 1); 
        
        // Send code to message queue
        if((status = sendMessage(queueID, code)) != 0) {
            break;
        }
        
        // Once machine sends offline signal we may exit
        if (code == DC_MACHINE_IS_OFFLINE) {
            logMessage(LOG_FILE, "DC [%d] - OFFLINED", getpid());
            break;
        }
    }
    
    return status;
}
