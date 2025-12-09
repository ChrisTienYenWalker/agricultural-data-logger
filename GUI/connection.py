import json
from PyQt5.QtWidgets import QWidget, QVBoxLayout, QLabel, QPushButton

class NetworkConnection(QWidget):
    def __init__(self):
        super().__init__()

        # Layout
        layout = QVBoxLayout()

        # Label
        self.label = QLabel("This is Tab 1")
        layout.addWidget(self.label)

        # Button
        self.button = QPushButton("Do something in Tab 1")
        self.button.clicked.connect(self.on_button_click)  # connect signal to function
        layout.addWidget(self.button)

        self.setLayout(layout)

    def on_button_click(self):
        # Example action: update label text
        self.label.setText("Button clicked in Tab 1")
        # Here you can add more logic, e.g., connect to a network or log data