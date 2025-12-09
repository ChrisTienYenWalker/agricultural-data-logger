from PyQt5.QtWidgets import QWidget, QVBoxLayout, QLabel, QPushButton

class Debug(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout()
        self.label = QLabel("This is Debug Tab")
        self.setLayout(layout)