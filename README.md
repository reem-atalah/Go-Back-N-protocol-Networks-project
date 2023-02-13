# Go-Back-N-protocol-Networks-project
Apply Go Back N protocol algorithm with noisy channel, using Byte stuffing as framing algorithm and parity byte as an error detection algorithm.

We considered 4 different types of noise that can attack the message where combination between errors on the same message has priority, we also, considered 4 types of delays. For furthur details, check [`Semester_Computer_Networks_Project_Fall2022.pdf`](Semester_Computer_Networks_Project_Fall2022.pdf)

The system consists of 2 nodes and a coordinator. 

The coordinator chooses which node will be sender and which will be a reciever.

The input file has all messages that should be sent, corresponds to the type of error that will occur on each message.

3 main parts are to be considered:

1.Messages
* Header: the data sequence number.
* Payload: the message contents after byte stuffing (in characters).
* Trailer: the parity byte. 
* Frame type: Data=0/ACK=1 /NACK=2.
* ACK/NACK number.

2.Framing
Done using the byte stuffing algorithm with starting and ending bytes

3.Error detection
Done using even parity byte, the parity byte checks for the payload after applying the byte stuffing and added at the trailer of the message. The receiver uses the parity byte to detect if there is/isn’t any single bit error during the 
transmission and so decides to send ACK/NACK

## Go Back N protocol

● The starting node reads the input file and starts sending data frame, and takes into account the four types of errors. It will send the frames within its sending window size (WS) with Propagation Time (PT) between frames as its processing speed. Sender considers messages that it didn't receive an ACK on it, to be resent after timeout with no errors

● Receiver responds with control frame for each data frame (i.e. no accumulative ACKs) ; “ACK” if no error and with “NACK” if there is an error, sending the control frame with a loss probability (LP).

● Each message data/control is given an id according to the Go Back N protocol and starts from zero and up to the window size and not to infinity.

● The session ends when the sender node finishes sending all the messages in its input file.
