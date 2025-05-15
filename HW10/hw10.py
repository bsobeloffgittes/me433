import matplotlib.pyplot as plt
import numpy as np
import csv


t = [] # column 0
data1 = [] # column 1

with open('sigD.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        data1.append(float(row[1])) # second column

# for i in range(len(t)):
#     # print the data to verify it was read
#     print(str(t[i]) + ", " + str(data1[i]))



# plt.plot(t,data1,'b-*')
# plt.xlabel('Time [s]')
# plt.ylabel('Signal')
# plt.title('Signal vs Time')
# plt.show()



# MOVING AVERAGE FILTER ------------------------------------------------------------

num_average = 500

filtered_arr = []



for i in range(len(t) - num_average):
    # print the data to verify it was read
    filtered_arr.append(sum(data1[i:(i+num_average)])/num_average)





Ts = (t[-1] - t[0]) / len(t) # sampling interval
Fs = 1.0 / Ts # sample rate
ts = np.arange(0,t[-1],Ts) # time vector
y = data1 # the data to make the fft from
y_filt = filtered_arr


n = len(y) # length of the 
n_filt = len(y_filt)

k = np.arange(n)
k_filt = np.arange(n_filt)

T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range

frq_filt = k/T # two sides frequency range
frq_filt = frq_filt[range(int(n_filt/2))] # one side frequency range

Y = np.fft.fft(y)/n # fft computing and normalization
Y = Y[range(int(n/2))]

Y_filt = np.fft.fft(y_filt)/n_filt # fft computing and normalization
Y_filt = Y_filt[range(int(n_filt/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t,y,'b')
ax1.plot(t[0:len(y_filt)],y_filt,'r')

ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')


ax2.loglog(frq,abs(Y),'b') # plotting the fft

ax2.loglog(frq_filt,abs(Y_filt),'r') # plotting the fft

ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.show()