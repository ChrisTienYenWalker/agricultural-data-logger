from PyQt5.QtWidgets import QWidget, QVBoxLayout, QLabel, QPushButton

class Config(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout()
        self.label = QLabel("This is Config Tab")
        self.setLayout(layout)