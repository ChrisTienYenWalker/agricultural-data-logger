from PyQt5.QtWidgets import QWidget, QVBoxLayout, QLabel, QPushButton

class Tab1(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout()
        self.label = QLabel("This is Tab 1")
        self.button = QPushButton("Do something in Tab 1")
        layout.addWidget(self.label)
        layout.addWidget(self.button)
        self.setLayout(layout)