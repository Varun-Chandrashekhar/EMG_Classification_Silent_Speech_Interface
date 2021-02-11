import serial
import streamlit as st
import pandas as pd

com_port = 'COM3'
baud = 115200

sensorData = serial.Serial(com_port, baud)

i = 0
signal = []
signal2 = []
title = []
while (i<3000):
    title.append(i+1)
    i=i+1
signal.append(title)
i=0
while (i < 3000):
    while (sensorData.inWaiting() == 0 and i==0):
        with st.spinner('Waiting for Data.....'):
            pass
    with st.spinner('Receiving Data.....'):
        signal2.append(sensorData.readline())
        i = i + 1
        print(i)

i=0
print(signal2)
while (i<3000):
    with st.spinner('Transforming Data.....'):
        if(i==1):
            print('Transforming Data')
        signal2[i] = signal2[i].decode('utf-8')
        signal2[i] = signal2[i].replace('\r\n', '')
        signal2[i] = int(signal2[i])
        i=i+1

signal.append(signal2)
print(signal)

with st.spinner('Saving Data as CSV.....'):
    df = pd.DataFrame(signal)
    df.to_csv('signal.csv', index=False, header=False)

print('SUccessfully COmpleted Code')