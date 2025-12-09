import sys
from PyQt5.QtWidgets import (
    QApplication, QWidget, QTabWidget, QVBoxLayout, QLabel
)


from connection import Tab1

from HomePage import Home
from DataPage import Data
from ConfigPage import Config
from DebugPage import Debug

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Agricultural Data Logger")
        self.setStyleSheet("background-color: #a87b32;")  
        
        layout = QVBoxLayout()
        self.tabs = QTabWidget()

        self.Home = Home()
        self.Data = Data()
        self.Config = Config()
        self.Debug = Debug()

        self.tabs.addTab(self.Home, "Home")
        self.tabs.addTab(self.Data, "Data")
        self.tabs.addTab(self.Config, "Config")
        self.tabs.addTab(self.Debug, "Debug")

        layout.addWidget(self.tabs)
        self.setLayout(layout)


app = QApplication(sys.argv)
window = MainWindow()
window.showMaximized()
sys.exit(app.exec_())
