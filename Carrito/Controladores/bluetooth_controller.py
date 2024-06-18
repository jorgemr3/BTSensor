import bluetooth


class BluetoothController:
    def _init_(self):
        self.nombre_carrito = "ESP32BT"
        self.mac_carrito = None
        self.conector = None

    def encontrar_carrito(self):
        dispositivos = bluetooth.discover_devices(lookup_names=True, lookup_class=True)

        for mac, nombre, clase_bt in dispositivos:
            if self.nombre_carrito == nombre:
                self.mac_carrito = mac
                break

        if self.mac_carrito is not None:
            print("Se encontró el dispositivo Bluetooth", self.nombre_carrito, "con la dirección", self.mac_carrito)
        else:
            print("No se pudo encontrar el dispositivo Bluetooth objetivo cercano")

    def conectar(self):

        if self.mac_carrito is not None:
            puerto = 1  # Puerto común para SPP (Serial Port Profile)
            self.conector = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
            self.conector.connect((self.mac_carrito, puerto))

            print("Conectado al dispositivo Bluetooth")

            return True
        else:
            print("No se pudo establecer la conexión con el dispositivo Bluetooth objetivo")
            return False

    def enviar_datos(self, datos):
        if self.conector is not None:
            self.conector.send(datos)
            print("Enviado:", datos)

    def recibir_datos(self):
        if self.conector is not None:
            respuesta = self.conector.recv(1024)
            print("Recibido:", respuesta)

    def cerrar_conexion(self):
        if self.conector is not None:
            self.conector.close()
            print("Conexión cerrada")

    def verificar_conexion(self):
        try:
            self.conector.send("")
            return True
        except:
            return False