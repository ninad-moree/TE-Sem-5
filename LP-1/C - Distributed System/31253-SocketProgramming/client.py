import socket

def client_program():
    # getting the host name for the client as both are running on same pc
    host = socket.gethostname()
    port = 5000    # socket server port number

    client_socket = socket.socket()  # instantiate
    # connect to the server
    client_socket.connect((host, port))

    message = input(' -> ')  # take input

    while message.lower().strip() != '&&':
        # send message
        client_socket.send(message.encode())
        # receive response
        data = client_socket.recv(1024).decode()

        print('Received from server: ' + data)  # show the message

        message = input('->')  # again take input

    # close the connection
    client_socket.close()


if __name__ == '__main__':
    client_program()
