import sys
import serial
import serial.tools.list_ports
from PyQt5.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QLabel, QPushButton, QTextEdit,
    QSizePolicy, QComboBox
)
from PyQt5.QtCore import QThread, pyqtSignal

# ---- Serial reading thread ----
class SerialReaderThread(QThread):
    data_received = pyqtSignal(str)

    def __init__(self, port, baudrate=115200):
        super().__init__()
        self.port_name = port
        self.baudrate = baudrate
        self.running = True

    def run(self):
        try:
            with serial.Serial(self.port_name, self.baudrate, timeout=1) as ser:
                while self.running:
                    if ser.in_waiting:
                        line = ser.readline().decode(errors='ignore').strip()
                        if line:
                            self.data_received.emit(line)
        except serial.SerialException as e:
            self.data_received.emit(f"Error opening {self.port_name}: {e}")

    def stop(self):
        self.running = False
        self.quit()
        self.wait()

# ---- Main Debug GUI ----
class Debug(QWidget):
    def __init__(self):
        super().__init__()

        main_layout = QVBoxLayout()

        # Status block
        status_block = QWidget()
        status_layout = QVBoxLayout()
        self.status_label = QLabel("Status: Idle")
        status_layout.addWidget(self.status_label)
        status_block.setLayout(status_layout)

        # Control block
        control_block = QWidget()
        control_layout = QHBoxLayout()
        self.start_button = QPushButton("Start Debug")
        self.stop_button = QPushButton("Stop Debug")
        self.stop_button.setEnabled(False)

        # COM port selector
        self.port_combo = QComboBox()
        self.refresh_ports_button = QPushButton("Refresh Ports")
        self.refresh_ports_button.clicked.connect(self.refresh_ports)
        self.refresh_ports()

        control_layout.addWidget(QLabel("COM Port:"))
        control_layout.addWidget(self.port_combo)
        control_layout.addWidget(self.refresh_ports_button)
        control_layout.addWidget(self.start_button)
        control_layout.addWidget(self.stop_button)
        control_block.setLayout(control_layout)
        control_block.setStyleSheet("background-color: grey;")

        # Wired log block
        log_block_wired = QWidget()
        log_layout_wired = QVBoxLayout()
        self.log_area_wired = QTextEdit()
        self.log_area_wired.setReadOnly(True)
        self.log_area_wired.setStyleSheet("background-color: black; color: white;")
        self.log_area_wired.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
        log_layout_wired.addWidget(QLabel("Debug Log Wired:"))
        log_layout_wired.addWidget(self.log_area_wired)
        log_block_wired.setLayout(log_layout_wired)
        log_block_wired.setStyleSheet("background-color: black;")

        # Wireless log block
        log_block_wireless = QWidget()
        log_layout_wireless = QVBoxLayout()
        self.log_area_wireless = QTextEdit()
        self.log_area_wireless.setReadOnly(True)
        self.log_area_wireless.setStyleSheet("background-color: black; color: white;")
        self.log_area_wireless.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
        log_layout_wireless.addWidget(QLabel("Debug Log Wireless:"))
        log_layout_wireless.addWidget(self.log_area_wireless)
        log_block_wireless.setLayout(log_layout_wireless)
        log_block_wireless.setStyleSheet("background-color: black;")

        main_layout.addWidget(status_block)
        main_layout.addWidget(control_block)
        main_layout.addWidget(log_block_wired)
        main_layout.addWidget(log_block_wireless)
        main_layout.addStretch(1)
        self.setLayout(main_layout)

        # Button connections
        self.start_button.clicked.connect(self.start_debug)
        self.stop_button.clicked.connect(self.stop_debug)

        # Serial thread
        self.serial_thread = None

    # ---- COM port detection ----
    def refresh_ports(self):
        self.port_combo.clear()
        ports = serial.tools.list_ports.comports()
        for port in ports:
            self.port_combo.addItem(port.device)

    # ---- Start debug ----
    def start_debug(self):
        port_name = self.port_combo.currentText()
        if port_name:
            self.serial_thread = SerialReaderThread(port_name)
            self.serial_thread.data_received.connect(self.append_wired_log)
            self.serial_thread.start()

        self.status_label.setText("Status: Running")
        self.log_area_wireless.append("Debug started...")
        self.log_area_wired.append("Debug started...")
        self.start_button.setEnabled(False)
        self.stop_button.setEnabled(True)

    # ---- Stop debug ----
    def stop_debug(self):
        if self.serial_thread:
            self.serial_thread.stop()
            self.serial_thread = None
        self.status_label.setText("Status: Stopped")
        self.log_area_wireless.append("Debug stopped.")
        self.log_area_wired.append("Debug stopped.")
        self.start_button.setEnabled(True)
        self.stop_button.setEnabled(False)

    # ---- Append data from serial ----
    def append_wired_log(self, text):
        self.log_area_wired.append(text)


# ---- Run example ----
if __name__ == "__main__":
    from PyQt5.QtWidgets import QApplication
    app = QApplication(sys.argv)
    window = Debug()
    window.resize(800, 600)
    window.show()
    sys.exit(app.exec_())
