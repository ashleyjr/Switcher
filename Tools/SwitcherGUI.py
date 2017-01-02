import random
import serial
import argparse
import wx
from matplotlib.figure import Figure    # matplotlib.use('WXAgg')
from matplotlib.backends.backend_wxagg import FigureCanvasWxAgg as FigCanvas
import pylab
import numpy as np

tick_ms = 1


class GraphFrame(wx.Frame):
    """ The main frame of the application
    """
    title = 'Switcher'

    def __init__(self,args):
        wx.Frame.__init__(self, None, -1, self.title)

        self.adc1_data = [0]
        self.adc2_data = [0]
        self.adc3_data = [0]
        self.plot_adc1_data = None
        self.plot_adc2_data = None
        self.plot_adc3_data = None
        self.adc1 = False
        self.adc2 = False
        self.adc3 = False
        self.fig = None
        self.axis = None
        self.panel = None
        self.canvas = None
        self.cb_adc1 = None
        self.cb_adc2 = None
        self.cb_adc3 = None
        self.hbox1 = None
        self.vbox = None

        self.enabled = True
        self.time = 0

        self.ser = serial.Serial(args.com_port, args.baud_rate)
        self.create_main_panel()
        self.redraw_timer = wx.Timer(self)
        self.Bind(wx.EVT_TIMER, self.on_redraw_timer, self.redraw_timer)
        self.redraw_timer.Start(1)

    def create_main_panel(self):
        self.panel = wx.Panel(self)

        self.init_plot()
        self.canvas = FigCanvas(self.panel, -1, self.fig)

        self.cb_enable = wx.CheckBox(self.panel, -1, "Enable", style=wx.ALIGN_LEFT)
        self.cb_enable.SetValue(False)

        self.cb_adc1 = wx.CheckBox(self.panel, -1, "Read input voltage", style=wx.ALIGN_LEFT)
        self.cb_adc1.SetValue(False)

        self.cb_adc2 = wx.CheckBox(self.panel, -1, "Read top side of current shunt", style=wx.ALIGN_LEFT)
        self.cb_adc2.SetValue(False)

        self.cb_adc3 = wx.CheckBox(self.panel, -1, "Read output voltage", style=wx.ALIGN_LEFT)
        self.cb_adc3.SetValue(False)

        self.hbox1 = wx.BoxSizer(wx.VERTICAL)
        self.hbox1.Add(self.cb_enable, border=5, flag=wx.ALL | wx.ALIGN_CENTER_VERTICAL)
        self.hbox1.Add(self.cb_adc1, border=5, flag=wx.ALL | wx.ALIGN_CENTER_VERTICAL)
        self.hbox1.Add(self.cb_adc2, border=5, flag=wx.ALL | wx.ALIGN_CENTER_VERTICAL)
        self.hbox1.Add(self.cb_adc3, border=5, flag=wx.ALL | wx.ALIGN_CENTER_VERTICAL)

        self.vbox = wx.BoxSizer(wx.HORIZONTAL)
        self.vbox.Add(self.canvas, 1, flag=wx.LEFT | wx.TOP | wx.GROW)
        self.vbox.Add(self.hbox1, 0, flag=wx.ALIGN_LEFT | wx.TOP)

        self.panel.SetSizer(self.vbox)
        self.vbox.Fit(self)

    def init_plot(self):
        self.fig = Figure((5.0, 5.0), 100)

        self.axes = self.fig.add_subplot(111)
        self.axes.set_axis_bgcolor('white')

        pylab.setp(self.axes.get_xticklabels(), fontsize=8)
        pylab.setp(self.axes.get_yticklabels(), fontsize=8)

        self.plot_adc1_data = self.axes.plot(self.adc1_data, color=(1, 0, 0), linewidth=1, )[0]
        self.plot_adc2_data = self.axes.plot(self.adc2_data, color=(0, 1, 0), linewidth=1, )[0]
        self.plot_adc3_data = self.axes.plot(self.adc3_data, color=(0, 0, 1), linewidth=1, )[0]

    def draw_plot(self):

        top = float(len(self.adc1_data)*tick_ms*100) / 1000
        time_s = np.linspace(0, top, len(self.adc1_data))
        xmin = 0
        xmax = time_s[len(time_s)-1]
        ymin = round(np.amin(np.concatenate([self.adc1_data, self.adc2_data, self.adc3_data])), 0) - 100
        ymax = round(np.amax(np.concatenate([self.adc1_data, self.adc2_data, self.adc3_data])), 0) + 100
        self.axes.set_xbound(lower=xmin, upper=xmax)
        self.axes.set_ybound(lower=ymin, upper=ymax)

        # anecdote: axes.grid assumes b=True if any other flag is
        # given even if b is set to False.
        # so just passing the flag into the first statement won't
        # work.
        #
        self.axes.grid(True, color='gray')

        self.plot_adc1_data.set_xdata(time_s)
        self.plot_adc2_data.set_xdata(time_s)
        self.plot_adc3_data.set_xdata(time_s)

        self.plot_adc1_data.set_ydata(np.array(self.adc1_data))
        self.plot_adc2_data.set_ydata(np.array(self.adc2_data))
        self.plot_adc3_data.set_ydata(np.array(self.adc3_data))

        self.canvas.draw()

    def sample(self, cmd):
        self.ser.flushInput()
        self.ser.write(cmd)
        while True:
            if self.ser.inWaiting() > 4:
                if self.ser.read(1) == cmd:
                    return int(self.ser.read(4))

    def on_redraw_timer(self, event):

        if 0 == self.time:
            """ Enable """
            if self.cb_enable.IsChecked() != self.enabled:
                self.enabled = self.cb_enable.IsChecked()
                if self.cb_enable.IsChecked():
                    self.ser.write("g")
                else:
                    self.ser.write("s")

        if 1 == self.time:
            """ ADC1 plotting"""
            if self.cb_adc1.IsChecked():
                self.adc1_data.append(self.sample("x"))
            else:
                self.adc1_data.append(self.adc1_data[len(self.adc1_data)-1])

        if 2 == self.time:
            """ ADC2 plotting"""
            if self.cb_adc2.IsChecked():
                self.adc2_data.append(self.sample("y"))
            else:
                self.adc2_data.append(self.adc2_data[len(self.adc2_data)-1])

        if 3 == self.time:
            """ ADC3 plotting"""
            if self.cb_adc3.IsChecked():
                self.adc3_data.append(self.sample("z"))
            else:
                self.adc3_data.append(self.adc3_data[len(self.adc3_data)-1])

        if 10 == self.time:
            self.draw_plot()
            self.time = 0
        else:
            self.time += 1

    def on_exit(self):
        self.Destroy()


def get_args():
    """Get command line arguments as a dictionary."""
    parser = argparse.ArgumentParser(description="Switcher serial")
    parser.add_argument('--port', dest='com_port', required=True, help='Serial port connected to switcher')
    parser.add_argument('--baud', dest='baud_rate', required=True, help='Baud rate for switcher UART')
    return parser.parse_args()


def main():
    args = get_args()
    app = wx.App(False)
    app.frame = GraphFrame(args)
    app.frame.Show()
    app.MainLoop()


if __name__ == '__main__':
    main()