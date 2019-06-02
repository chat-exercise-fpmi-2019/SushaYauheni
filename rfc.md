# Chat protocol (in development)

This document describes network protocol for "client-server chat" educational exercise.

The chat consist of server and client. Client can issue three types of commands:
- Set username
- Send private message
- Send broadcast message

Server can send two types of message to client.
- Incoming message
- Response code

---

### Connection
Clients establishes a **TCP** (see RFC 793) connection with a server and communicates with text messages.

Clients and servers MAY do anything, including dropping the connection, after receiving a message badly formed according to this RFC.

---
### Nick format

Single letters

Words (strings without spaces)

---

## Messages send from client to server

**Length-prefixed: At the beginning of each message a number of bytes, that consists of 4 digits, specifying length of message is added, followed by space.**

---
### User messages
Command: "[n] USER [nick]"
The USER command is used at the beginning of connection to specify  the username.
[n] - length of message
[nick] - username of user

| Example	| Description |
| --- | --- |
| 0007 USER G | User with nickname "G" is connecting |

##### Responses:
NICKCOLLISION
NICKFORMAT
OK

****
### Private messages
Command: "[n] PMSG [msgtarget] [msg]"
- [n] - length of message
- [msgtarget] is the nickname of the recipient of the message
- [msg] is text to be send to another user

| Example	| Description |
| --- | --- |
| 0013 PMSG G hello | User sending message "hello" to user with nickname "G" |

##### Responses:
NOLOGIN
EMPTYMESG
USERNOTEXIST
OK

---
### Broadcast messages
Command: "[n] BMSG [msg]"
- [n] - length of message
- [msg] - text to be send to all users

| Example	| Description |
| --- | --- |
| 0020 BMSG blah blah blah | User sending message "blah blah blah" to all another user |

##### Responses:
NOLOGIN
EMPTYMESG
OK

---
### Quit messages
Command: \|QUIT\|

A client session is terminated with a quit message.
##### Responses:
none

---
## Messages send from server to client

### Incoming messages
Format: "[n] MESG [from] [msg]"
- [n] - length of the message
- [from] - sender nickname
- [msg] - message text

---
### Responses

| Response code           | Response name  | Description  |
|-------------------------|----------------|--------------|
|0                        | OK             | Success - The action was successfully done  |
|1                        | NICKCOLLISION  | Returned by a server when user try enter with nickname that is already  taken |
|2                        | NICKFORMAT     | Incorrect nickname                    |
|3                        | EMPTYMESG      | User send empty message                  |
|4                        | USERNOTEXIST   | User is send message to not existing or already disconected user  |
|5                        | NOLOGIN        | Returned by a server when trying to send message before login                  |
|6                        | NOCOMMAND      | No such command
