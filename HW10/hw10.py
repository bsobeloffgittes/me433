import matplotlib.pyplot as plt
import numpy as np
import csv


t = [] # column 0
data1 = [] # column 1

filename = 'sigD.csv'

with open(filename) as f:
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

# num_average = 1000

# filtered_arr = []



# for i in range(len(t) - num_average):
#     # print the data to verify it was read
#     filtered_arr.append(sum(data1[i:(i+num_average)])/num_average)





# Ts = (t[-1] - t[0]) / len(t) # sampling interval
# Fs = 1.0 / Ts # sample rate
# ts = np.arange(0,t[-1],Ts) # time vector
# y = data1 # the data to make the fft from
# y_filt = filtered_arr


# n = len(y) # length of the 
# n_filt = len(y_filt)

# k = np.arange(n)
# k_filt = np.arange(n_filt)

# T = n/Fs
# frq = k/T # two sides frequency range
# frq = frq[range(int(n/2))] # one side frequency range

# frq_filt = k/T # two sides frequency range
# frq_filt = frq_filt[range(int(n_filt/2))] # one side frequency range

# Y = np.fft.fft(y)/n # fft computing and normalization
# Y = Y[range(int(n/2))]

# Y_filt = np.fft.fft(y_filt)/n_filt # fft computing and normalization
# Y_filt = Y_filt[range(int(n_filt/2))]

# fig, (ax1, ax2) = plt.subplots(2, 1)
# ax1.plot(t,y,'b')
# ax1.plot(t[0:len(y_filt)],y_filt,'r')

# ax1.set_xlabel('Time')
# ax1.set_ylabel('Amplitude')


# ax2.loglog(frq,abs(Y),'b') # plotting the fft

# ax2.loglog(frq_filt,abs(Y_filt),'r') # plotting the fft

# ax2.set_xlabel('Freq (Hz)')
# ax2.set_ylabel('|Y(freq)|')

# fig.suptitle(f'{filename} MAF: {num_average} samples averaged')

# plt.show()

# IIR --------------------------------------------------------

# A = 0.003
# B = 0.997

# filtered_arr = [data1[0]]

# avg = 0

# for i in range(len(t) - 1):
#     # print the data to verify it was read
#     filtered_arr.append(A * data1[i+1] + B * filtered_arr[-1])



# Ts = (t[-1] - t[0]) / len(t) # sampling interval
# Fs = 1.0 / Ts # sample rate
# ts = np.arange(0,t[-1],Ts) # time vector
# y = data1 # the data to make the fft from
# y_filt = filtered_arr


# n = len(y) # length of the 
# n_filt = len(y_filt)

# k = np.arange(n)
# k_filt = np.arange(n_filt)

# T = n/Fs
# frq = k/T # two sides frequency range
# frq = frq[range(int(n/2))] # one side frequency range

# frq_filt = k/T # two sides frequency range
# frq_filt = frq_filt[range(int(n_filt/2))] # one side frequency range

# Y = np.fft.fft(y)/n # fft computing and normalization
# Y = Y[range(int(n/2))]

# Y_filt = np.fft.fft(y_filt)/n_filt # fft computing and normalization
# Y_filt = Y_filt[range(int(n_filt/2))]

# fig, (ax1, ax2) = plt.subplots(2, 1)
# ax1.plot(t,y,'b')
# ax1.plot(t[0:len(y_filt)],y_filt,'r')

# ax1.set_xlabel('Time')
# ax1.set_ylabel('Amplitude')


# ax2.loglog(frq,abs(Y),'b') # plotting the fft

# ax2.loglog(frq_filt,abs(Y_filt),'r') # plotting the fft

# ax2.set_xlabel('Freq (Hz)')
# ax2.set_ylabel('|Y(freq)|')

# fig.suptitle(f'{filename} IIR Plot: A = {A}, B = {B}')
# plt.show()


# FIR ------------------------------------------------------------------------

h = [
    0.000000000000000000,
    0.000000145404338621,
    0.000000555575539163,
    0.000001185942434145,
    0.000001984607885523,
    0.000002892388160588,
    0.000003842877389819,
    0.000004762544754746,
    0.000005570872996230,
    0.000006180547626520,
    0.000006497706848471,
    0.000006422262611541,
    0.000005848303447992,
    0.000004664589718870,
    0.000002755151645497,
    0.000000000000000000,
    -0.000003724041427130,
    -0.000008542373473977,
    -0.000014581522520510,
    -0.000021967899323895,
    -0.000030826412167037,
    -0.000041278932663488,
    -0.000053442614710410,
    -0.000067428069403219,
    -0.000083337401193829,
    -0.000101262113159020,
    -0.000121280891913072,
    -0.000143457285414002,
    -0.000167837289637491,
    -0.000194446862787729,
    -0.000223289388339129,
    -0.000254343110716253,
    -0.000287558569779833,
    -0.000322856062454051,
    -0.000360123161764237,
    -0.000399212325217169,
    -0.000439938625812120,
    -0.000482077639986717,
    -0.000525363527447701,
    -0.000569487338086697,
    -0.000614095581013164,
    -0.000658789090133609,
    -0.000703122219655399,
    -0.000746602401388159,
    -0.000788690093754049,
    -0.000828799150004300,
    -0.000866297630283093,
    -0.000900509078896742,
    -0.000930714284457679,
    -0.000956153536505927,
    -0.000976029387798135,
    -0.000989509926733592,
    -0.000995732559400569,
    -0.000993808295521939,
    -0.000982826527207600,
    -0.000961860283937304,
    -0.000929971941658895,
    -0.000886219358353572,
    -0.000829662402953388,
    -0.000759369839159349,
    -0.000674426520564309,
    -0.000573940848595693,
    -0.000457052440220375,
    -0.000322939948157168,
    -0.000170828972577949,
    0.000000000000000000,
    0.000190203697671243,
    0.000400368273153349,
    0.000631001693600885,
    0.000882526381863242,
    0.001155272181039943,
    0.001449469713700035,
    0.001765244205932193,
    0.002102609844473788,
    0.002461464732532130,
    0.002841586506569255,
    0.003242628672290262,
    0.003664117713379691,
    0.004105451021203207,
    0.004565895687773317,
    0.005044588197814543,
    0.005540535048809659,
    0.006052614320523339,
    0.006579578207748587,
    0.007120056521974671,
    0.007672561159407321,
    0.008235491524360532,
    0.008807140888565053,
    0.009385703658484061,
    0.009969283514374389,
    0.010555902376666433,
    0.011143510147339221,
    0.011729995166420459,
    0.012313195316623312,
    0.012890909702516601,
    0.013460910824584124,
    0.014020957163127552,
    0.014568806082265101,
    0.015102226960329078,
    0.015619014449815016,
    0.016117001767722013,
    0.016594073915679158,
    0.017048180728697442,
    0.017477349651734558,
    0.017879698144514681,
    0.018253445617202480,
    0.018596924802575618,
    0.018908592474250328,
    0.019187039425258179,
    0.019430999626808561,
    0.019639358493352382,
    0.019811160187032037,
    0.019945613902197162,
    0.020042099078816079,
    0.020100169502243356,
    0.020119556255834326,
    0.020100169502243356,
    0.020042099078816079,
    0.019945613902197162,
    0.019811160187032040,
    0.019639358493352382,
    0.019430999626808564,
    0.019187039425258182,
    0.018908592474250328,
    0.018596924802575618,
    0.018253445617202480,
    0.017879698144514681,
    0.017477349651734558,
    0.017048180728697442,
    0.016594073915679158,
    0.016117001767722017,
    0.015619014449815016,
    0.015102226960329080,
    0.014568806082265103,
    0.014020957163127554,
    0.013460910824584124,
    0.012890909702516596,
    0.012313195316623312,
    0.011729995166420462,
    0.011143510147339223,
    0.010555902376666437,
    0.009969283514374391,
    0.009385703658484063,
    0.008807140888565055,
    0.008235491524360532,
    0.007672561159407324,
    0.007120056521974672,
    0.006579578207748588,
    0.006052614320523342,
    0.005540535048809659,
    0.005044588197814543,
    0.004565895687773319,
    0.004105451021203207,
    0.003664117713379690,
    0.003242628672290262,
    0.002841586506569257,
    0.002461464732532131,
    0.002102609844473790,
    0.001765244205932194,
    0.001449469713700036,
    0.001155272181039943,
    0.000882526381863242,
    0.000631001693600885,
    0.000400368273153349,
    0.000190203697671243,
    0.000000000000000000,
    -0.000170828972577949,
    -0.000322939948157167,
    -0.000457052440220375,
    -0.000573940848595693,
    -0.000674426520564310,
    -0.000759369839159349,
    -0.000829662402953388,
    -0.000886219358353573,
    -0.000929971941658895,
    -0.000961860283937306,
    -0.000982826527207601,
    -0.000993808295521939,
    -0.000995732559400568,
    -0.000989509926733592,
    -0.000976029387798135,
    -0.000956153536505928,
    -0.000930714284457679,
    -0.000900509078896743,
    -0.000866297630283094,
    -0.000828799150004300,
    -0.000788690093754051,
    -0.000746602401388159,
    -0.000703122219655399,
    -0.000658789090133609,
    -0.000614095581013164,
    -0.000569487338086698,
    -0.000525363527447702,
    -0.000482077639986717,
    -0.000439938625812120,
    -0.000399212325217169,
    -0.000360123161764237,
    -0.000322856062454053,
    -0.000287558569779833,
    -0.000254343110716253,
    -0.000223289388339129,
    -0.000194446862787728,
    -0.000167837289637491,
    -0.000143457285414002,
    -0.000121280891913073,
    -0.000101262113159020,
    -0.000083337401193830,
    -0.000067428069403219,
    -0.000053442614710410,
    -0.000041278932663488,
    -0.000030826412167037,
    -0.000021967899323895,
    -0.000014581522520510,
    -0.000008542373473977,
    -0.000003724041427130,
    0.000000000000000000,
    0.000002755151645497,
    0.000004664589718870,
    0.000005848303447992,
    0.000006422262611541,
    0.000006497706848471,
    0.000006180547626520,
    0.000005570872996230,
    0.000004762544754746,
    0.000003842877389819,
    0.000002892388160588,
    0.000001984607885523,
    0.000001185942434145,
    0.000000555575539163,
    0.000000145404338621,
    0.000000000000000000,
]

h = np.array(h)

fir_len = len(h)

filtered_arr = [data1[fir_len]]

data_buf = data1[0:fir_len]

for i in range(len(t) - fir_len):
    # print the data to verify it was read
    

    filtered_arr.append(np.dot(h, data_buf))

    data_buf = np.delete(data_buf, 0)
    data_buf = np.append(data_buf, data1[fir_len + i])



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

fig.suptitle(f'{filename} FIR Plot: n = {fir_len}, cutoff frequency = 100 Hz')
plt.show()