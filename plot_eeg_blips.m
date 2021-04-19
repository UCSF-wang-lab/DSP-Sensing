%% required input

filename = 'ecg_dummy_data2';
fs = 2000;
% total_time = 10;

%% read file, plot filtered and unfiltered

a = fopen(filename);
% signal = fread(a,inf,'double');
signal = textscan(a,'%s');
signal = str2num(cell2mat(signal{1,1}));
fclose(a);

% t = 0:1/fs:total_time-1/fs;
t = 1:length(signal);

filtered = bandstop(signal,[40,70],fs);

% titL = '4kHz sampling, 1 sec recording, 5Hz stim, 60us pulse width @ 2mA';


fig1 = figure(1);
plot(t,signal);
% title(titL);
xlabel('Time (s)')
ylabel('Analog')
ylim([0,1000])

fig2 = figure(2);
plot(periodogram(signal));
% title(titL);
xlabel('Frequency (Hz)')
xlim([1,100])
ylim([0,1000000])

% ylabel('dB')

fig3 = figure(3);
plot(t,filtered);
% title(titL);
xlabel('Time (s)')
ylabel('Analog')
ylim([0,1000])

fig4 = figure(4);
plot(periodogram(filtered));
% title(titL);
xlabel('Frequency (Hz)')
xlim([1,100])
ylim([0,1000000])
