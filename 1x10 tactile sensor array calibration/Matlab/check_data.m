clear all
close all

load('dataset.mat')
%cell{1}.time = [1;2;3]
% for i = 1 : 10
%     cell{i}.time_sen = []
%     cell{i}.time_f = []
%     cell{i}.val_sen = []
%     cell{i}.val_f = []
%     
% end
% for i = 1 : 10
%     cell{i}.time_f = cell{i}.time_f/1000;
% end
%% plot
for i = 1 : 10
    figure(i)
    subplot(2,1,1)
    plot(cell{i}.time_sen,1./cell{i}.val_sen)
    xlim([0, max([cell{i}.time_sen;cell{i}.time_f])])
    subplot(2,1,2)
    plot(cell{i}.time_f,cell{i}.val_f)
    xlim([0, max([cell{i}.time_sen;cell{i}.time_f])])
end

%% ±Ø´ë Á¡ Ã£±â
clear local_max
range_len = 50;

for i = 1 : 10
    k = 1;
    for ii = 1 :length(cell{i}.val_sen)
        op = 1 ;
        for val = 0 : range_len-1
            range0 = max(ii-range_len+1+val,1) : min(ii+val,length(cell{i}.val_sen));
            [A,B] = max(1./cell{i}.val_sen(range0));
            range0(B);
            if range0(B) == ii
                op = op*1;
            else
                op = op*0;
            end
        end
        if op ==1
            local_max{i}(k) = ii;
            k = k+1;
        end
    end
end

% plot
close all

for i = 1 : 10
    figure(i)
    subplot(2,1,1)
    plot(cell{i}.time_sen,1./cell{i}.val_sen)
    xlim([0, max([cell{i}.time_sen;cell{i}.time_f])])
    hold on;
    plot (cell{i}.time_sen(local_max{i}),1./cell{i}.val_sen(local_max{i}),'.')
    subplot(2,1,2)
    plot(cell{i}.time_f,cell{i}.val_f)
    xlim([0, max([cell{i}.time_sen;cell{i}.time_f])])
end

for i = 1 : 10 
    result{i} = 1./cell{i}.val_sen(local_max{i})
end