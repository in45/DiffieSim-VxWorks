#include <stdio.h>
#include <stdlib.h>
#include <taskLib.h>
#include <msgQLib.h>

#define PRIMITIVE_ROOT 5
#define PRIME_NUMBER   23

typedef struct {
    int publicValue;
} DHMessage;

MSG_Q_ID msgQIdAliceToBob;
MSG_Q_ID msgQIdBobToAlice;

int modPow(int base, int exponent, int modulus) {
    int result = 1;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

void taskAlice(void) {
    int privateAlice = 6;
    int publicAlice;
    int publicBob;
    int sharedSecretAlice;
    DHMessage message;

    publicAlice = modPow(PRIMITIVE_ROOT, privateAlice, PRIME_NUMBER);

    message.publicValue = publicAlice;
    msgQSend(msgQIdAliceToBob, (char *)&message, sizeof(message), WAIT_FOREVER, MSG_PRI_NORMAL);

    msgQReceive(msgQIdBobToAlice, (char *)&message, sizeof(message), WAIT_FOREVER);
    publicBob = message.publicValue;

    sharedSecretAlice = modPow(publicBob, privateAlice, PRIME_NUMBER);
    printf("Alice's Shared Secret: %d\n", sharedSecretAlice);
}

void taskBob(void) {
    int privateBob = 15;
    int publicBob;
    int publicAlice;
    int sharedSecretBob;
    DHMessage message;

    publicBob = modPow(PRIMITIVE_ROOT, privateBob, PRIME_NUMBER);

    msgQReceive(msgQIdAliceToBob, (char *)&message, sizeof(message), WAIT_FOREVER);
    publicAlice = message.publicValue;

    message.publicValue = publicBob;
    msgQSend(msgQIdBobToAlice, (char *)&message, sizeof(message), WAIT_FOREVER, MSG_PRI_NORMAL);

    sharedSecretBob = modPow(publicAlice, privateBob, PRIME_NUMBER);
    printf("Bob's Shared Secret: %d\n", sharedSecretBob);
}

void initMessageQueues() {
    int queueSize = 10;
    int maxMessageLength = sizeof(DHMessage);

    msgQIdAliceToBob = msgQCreate(queueSize, maxMessageLength, MSG_Q_FIFO);
    msgQIdBobToAlice = msgQCreate(queueSize, maxMessageLength, MSG_Q_FIFO);

    if (msgQIdAliceToBob == NULL || msgQIdBobToAlice == NULL) {
        printf("Error: Unable to create message queues\n");
        exit(1);
    }
}

int main(void) {
    initMessageQueues();

    taskSpawn("taskAlice", 100, 0, 10000, (FUNCPTR)taskAlice, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    taskSpawn("taskBob", 100, 0, 10000, (FUNCPTR)taskBob, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    return 0;
}
