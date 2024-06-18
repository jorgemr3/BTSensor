import sys
from PyQt5 import uic, QtWidgets

#import recursos_rc

from carrito_controller import CarritoController

Ui_MainWindow, QtBaseClass = uic.loadUiType('main.ui')

class MyApp(QtWidgets.QMainWindow, Ui_MainWindow):
    def _init_(self):
        QtWidgets.QMainWindow._init_(self)
        Ui_MainWindow._init_(self)
        self.setupUi(self)

        self.conectado = False

        self.controller = CarritoController(self, QtWidgets)

        self.bArriba.clicked.connect(self.controller.avanzar)
        self.bIzq.clicked.connect(self.controller.izquierda)
        self.bDer.clicked.connect(self.controller.derecha)
        self.bAbajo.clicked.connect(self.controller.retroceder)
        self.bTruco.clicked.connect(self.controller.truco)
        self.bDetener.clicked.connect(self.controller.detener)
        self.bConectar.clicked.connect(self.controller.conectar)

if __name__ == "_main_":
    app = QtWidgets.QApplication(sys.argv)
    window = MyApp()
    window.show()
    sys.exit(app.exec_())