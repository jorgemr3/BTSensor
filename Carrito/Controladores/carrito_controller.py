from bluetooth_controller import BluetoothController

class CarritoController:
    def _init_(self, main, qtWidgets):
        self.main = main
        self.qtWidgets = qtWidgets
        self.bluetooth_controller = BluetoothController()

    def enviar_comando(self, comando):
        if self.bluetooth_controller.verificar_conexion():
            self.bluetooth_controller.enviar_datos(comando)
        else:
            self.qtWidgets.QMessageBox.critical(self.main, "Error", "No se pudo establecer la conexión con el carrito")

    def avanzar(self):
        self.enviar_comando("F")

    def retroceder(self):
        self.enviar_comando("B")

    def izquierda(self):
        self.enviar_comando("L")

    def derecha(self):
        self.enviar_comando("R")

    def detener(self):
        self.enviar_comando("S")

    def truco(self, mensaje):
        self.enviar_comando(mensaje)

    def conectar(self):
        # mientras este buscando y conectando, mostrar un dialogo de espera
        dialogo = self.qtWidgets.QProgressDialog("Conectando...", "Cancelar", 0, 0, self.main)
        dialogo.setWindowModality(2)
        dialogo.show()
        dialogo.setValue(0)
        dialogo.setLabelText("Buscando dispositivo...")
        # buscar el dispositivo
        self.bluetooth_controller.encontrar_carrito()
        dialogo.setValue(50)
        # conectar al dispositivo
        dialogo.setLabelText("Conectando al dispositivo...")
        dialogo.setValue(100)
        if self.bluetooth_controller.conectar():
            self.main.conectado = True
            self.qtWidgets.QMessageBox.information(self.main, "Conexión exitosa", "Conexión exitosa con el carrito")
        else:
            self.main.conectado = False
            self.qtWidgets.QMessageBox.critical(self.main, "Error", "No se pudo establecer la conexión con el carrito")
        dialogo.close()