from PyQt5.QtWidgets import QWidget, QVBoxLayout, QLabel, QPushButton

class Data(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout()
        self.label = QLabel("This is Data Tab")
        self.setLayout(layout)