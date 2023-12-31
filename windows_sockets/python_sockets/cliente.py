import socket

mi_socket = socket.socket()

mi_socket.connect( ('localhost', 15001) )

#mi_socket.send('hola desde el cliente')
respuesta = mi_socket.recv(100)

print(respuesta)
mi_socket.close()
