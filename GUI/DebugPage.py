from PyQt5.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout, QLabel, QPushButton, QTextEdit, QSizePolicy

class Debug(QWidget):
    def __init__(self):
        super().__init__()

        main_layout = QVBoxLayout()

        status_block = QWidget()
        status_layout = QVBoxLayout()
        self.status_label = QLabel("Status: Idle")
        status_layout.addWidget(self.status_label)
        status_block.setLayout(status_layout)

        control_block = QWidget()
        control_layout = QHBoxLayout()
        self.start_button = QPushButton("Start Debug")
        self.stop_button = QPushButton("Stop Debug")
        control_layout.addWidget(self.start_button)
        control_layout.addWidget(self.stop_button)
        control_block.setLayout(control_layout)
        control_block.setStyleSheet("background-color: grey;")  
                
        log_block_wireless = QWidget()
        log_layout_wireless = QVBoxLayout()
        self.log_area_wireless = QTextEdit()
        self.log_area_wireless.setReadOnly(True)
        self.log_area_wireless.setStyleSheet("background-color: black; color: white;")
        self.log_area_wireless.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Fixed)  
        log_layout_wireless.addWidget(QLabel("Debug Log Wireless:"))
        log_layout_wireless.addWidget(self.log_area_wireless)
        log_block_wireless.setLayout(log_layout_wireless)
        log_block_wireless.setStyleSheet("background-color: black;")  

        log_block_wired = QWidget()
        log_layout_wired = QVBoxLayout()
        self.log_area_wired = QTextEdit()
        self.log_area_wired.setReadOnly(True)
        self.log_area_wired.setStyleSheet("background-color: black; color: white;")
        self.log_area_wired.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Fixed)  
        log_layout_wired.addWidget(QLabel("Debug Log Wired:"))
        log_layout_wired.addWidget(self.log_area_wired)
        log_block_wired.setLayout(log_layout_wired)
        log_block_wired.setStyleSheet("background-color: black;")  
        
        main_layout.addWidget(status_block)
        main_layout.addWidget(control_block)
        main_layout.addWidget(log_block_wired)
        main_layout.addWidget(log_block_wireless)
        main_layout.addStretch(1)  
        
        self.setLayout(main_layout)

        self.start_button.clicked.connect(self.start_debug)
        self.stop_button.clicked.connect(self.stop_debug)

    # Example methods
    def start_debug(self):
        self.status_label.setText("Status: Running")
        self.log_area_wireless.append("Debug started...")
        self.log_area_wired.append("Debug started...")

    def stop_debug(self):
        self.status_label.setText("Status: Stopped")
        self.log_area_wireless.append("Debug stopped.")
        self.log_area_wired.append("Debug stopped.")
