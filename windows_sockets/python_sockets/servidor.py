import socket

#s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
mi_socket = socket.socket()

mi_socket.bind( ('localhost',15001) )

mi_socket.listen(5)

while True:
    print("Esperando conexiones")
    conexion, addr = mi_socket.accept()
    print("Nueva conexion")
    print(addr)
    #peticion = conexion.recv(1024)
    #print( peticion )
    conexion.send("hola", 100)
    conexion.close()
