# DiffieSim: VxWorks Secure Key Exchange

## Overview

This project demonstrates a simple implementation of the Diffie-Hellman key exchange protocol using VxWorks real-time operating system. The simulation involves two tasks, `taskAlice` and `taskBob`, which communicate over message queues to exchange public keys and compute a shared secret.

## Key Features

- **Diffie-Hellman Protocol**: Implements the basic principles of the Diffie-Hellman key exchange to securely share a secret key over an insecure channel.
- **VxWorks Tasks**: Utilizes VxWorks tasks to simulate Alice and Bob in the key exchange process.
- **Message Queues**: Employs VxWorks message queues for inter-task communication.

## Components

1. **modPow**: Computes modular exponentiation efficiently.
2. **taskAlice**: Simulates Alice's role in the key exchange, including sending her public key and computing the shared secret based on Bob's public key.
3. **taskBob**: Simulates Bob's role, including sending his public key and computing the shared secret based on Alice's public key.
4. **initMessageQueues**: Initializes the message queues used for communication between tasks.

## Setup and Execution

1. **Compile the Code**:
   Compile the code using your VxWorks development environment.

2. **Run the Simulation**:
   Execute the program in your VxWorks environment. The tasks will be spawned, and the key exchange will occur automatically.

## Contribution

Feel free to modify the code and extend the functionality. Contributions and improvements are welcome!

---

Enjoy exploring the Diffie-Hellman key exchange protocol with this VxWorks simulation!

