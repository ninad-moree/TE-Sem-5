import socket


def server_program():
    # get the hstname
    host = socket.gethostname()
    port = 5000     # initiatiate port no. above 1024

    server_socket = socket.socket()  # get instance

    # bind host adderss and port together
    server_socket.bind((host, port))

    # configure how many clients the server can listen simultaneously
    server_socket.listen(2)

    # accept a connection
    conn, addr = server_socket.accept()
    print("Connection from : " + str(addr))

    while True:
        # receive data stream
        # Setting data packet limit 1024
        data = conn.recv(1024).decode()

        if not data:
            # if data is not received then break
            break

        print("from connected user: " + str(data))
        data = input(' -> ')
        conn.send(data.encode())  # send data to the client

    # close the connection
    conn.close()


if __name__ == '__main__':
    server_program()
