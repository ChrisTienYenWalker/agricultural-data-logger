import json
from PyQt5.QtWidgets import QWidget, QVBoxLayout, QLabel, QPushButton

class Home(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout()
        self.label = QLabel("This is Home Tab")
        self.setLayout(layout)