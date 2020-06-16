close all
clear
clc

struct_1 = importdata('Messungen_kleine_Box.txt')
plot(struct_1.data(:,2)*1e3, struct_1.data(:,1)./struct_1.data(:,2))
grid minor
hold on
xlabel('I_{Meas} in mA')
ylabel('R_{PT100} in \Omega')