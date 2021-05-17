%% required input

filename = 'rcs14_olclickc_80sec_NECKFOOT';
fs = 4000;

%% read file, plot filtered and unfiltered

a = fopen(filename);
% signal = fread(a,inf,'double');
s = textscan(a,'%s');
% signal = cell2mat(signal{1,1});
% signal = str2num(signal);

signal = [];
n = size(s{1,1}, 1);
for i = 1:n
    signal = [signal str2num(s{1,1}{i})];
end

fclose(a);

total_time = length(signal)/fs;
t = 0:1/fs:total_time-1/fs;
% t = 1:length(signal);

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

saveas(fig1,'fig1','fig')
saveas(fig2,'fig2','fig')
saveas(fig3,'fig3','fig')
saveas(fig4,'fig4','fig')
