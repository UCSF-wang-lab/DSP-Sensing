% required input

% filename = 'singleeeg_twoipgs_leftclavicle_120us_2nd';
%%%% this works tho the right side isn't THAT big of a deflection
% 
% filename = 'singleeeg_twoipgs_leftclavicle_200us';
%%%% this looks good, tho you can see the little 0mA pulses throughout

% filename = 'singleeeg_twodiagonal_leftclavicle_200us';
%looks pretty good

% filename = 'singleeeg_twodiagonal_leftribs_200';
%nope

filename = 'singleecg5_twoipgs_leftclavicle_200us_3rd';
% filename = 'singleolimex_twoipgs_leftclavicle_200us';





% NEED TO TEST ECG 5 NEVER BEEN TESTED
% AND GAIN IS INCREASED ON OLIMEX

fs = 4000;

data = ConvertTeensyTxt(filename);

% plot filtered and unfiltered
EEGLeft = data.EEGLeft;
EEGRight = data.EEGRight;
time = data.ElapsedMicros-data.ElapsedMicros(1);
time = time/1000000;

EEGLeft_filtered = bandstop(EEGLeft,[40,70],fs);
EEGRight_filtered = bandstop(EEGRight,[40,70],fs);

fig1_title = 'Left Raw';
fig1 = figure(1);
fig1.Position = [0,600,850,400];
plot(time,EEGLeft);
title(fig1_title);
xlabel('Time (s)')
ylabel('Analog')
ylim([0,1000])

fig2_title = 'Left Filtered';
fig2 = figure(2);
fig2.Position = [900,600,850,400];
plot(time,EEGLeft_filtered);
title(fig2_title);
xlabel('Time (s)')
ylabel('Analog')
ylim([0,1000])

fig3_title = 'Right Raw';
fig3 = figure(3);
fig3.Position = [0,80,850,400];
plot(time,EEGRight);
title(fig3_title);
xlabel('Time (s)')
ylabel('Analog')
ylim([0,1000])

fig4_title = 'Right Filtered';
fig4 = figure(4);
fig4.Position = [900,80,850,400];
plot(time,EEGRight_filtered);
title(fig4_title);
xlabel('Time (s)')
ylabel('Analog')
ylim([0,1000])

% fig2 = figure(2);
% plot(periodogram(signal));
% title(titL);
% xlabel('Frequency (Hz)')
% xlim([1,100])
% ylim([0,1000000])
% ylabel('dB')

% fig3 = figure(3);
% plot(t,filtered);
% title(titL);
% xlabel('Time (s)')
% ylabel('Analog')
% ylim([0,1000])
% 
% fig4 = figure(4);
% plot(periodogram(filtered));
% title(titL);
% xlabel('Frequency (Hz)')
% xlim([1,100])
% ylim([0,1000000])

saveas(fig1,[filename,'_',fig1_title],'fig')
saveas(fig2,[filename,'_',fig2_title],'fig')
saveas(fig3,[filename,'_',fig3_title],'fig')
saveas(fig4,[filename,'_',fig4_title],'fig')
