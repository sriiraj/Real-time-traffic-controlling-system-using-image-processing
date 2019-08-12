clc
clear all
close all

cam=webcam(2);

bg=snapshot(cam);

%%
fg=snapshot(cam);

tic
[f1,f2,f3,f4]=crop(fg);
[b1,b2,b3,b4]=crop(bg);
x1=processing(f1,b1);
x2=processing(f2,b2);
x3=processing(f3,b3);
x4=processing(f4,b4);
x1= num2str(x1);
x2= num2str(x2);
x3= num2str(x3);
x4= num2str(x4);
toc

I=fg;
Irgb=I;
colorTransform = makecform('srgb2lab');
I = applycform(I, colorTransform);
b = I(:,:,3);
%figure,imshow(b)
I=double(b);
%figure,imshow(I)
Imin=min(I(:));
Imax=max(I(:));
I=(I-Imin)/(Imax-Imin);
I3 = imbinarize(I,0.9);
figure,imshow(I)
figure,imshow(I3)
BW2 = edge(I3,'canny');
B = bwboundaries(BW2);
b2 = imcrop(BW2,[5 162 205 195]);
figure,imshow(b2);
c2 = imcrop(BW2,[206 2 200 155]);
figure,imshow(c2);
d2 = imcrop(BW2,[405 155 233 191]);
figure,imshow(d2);
e2 = imcrop(BW2,[216 354 190 122]);
figure,imshow(e2);
B = bwboundaries(b2);
y1 = int8(length(B)/2);
disp(y1);

B = bwboundaries(c2);
y2 = int8(length(B)/2);
disp(y2);

B = bwboundaries(d2);
y3 = int8(length(B)/2);
disp(y3);

B = bwboundaries(e2);
y4 = int8(length(B)/2);
disp(y4);

if y1 > 0
     x5 = str2num(x1);
     display(x5);
     x1 = x5+10;
     x1 = num2str(x1);
elseif y2 > 0
     x5 = str2num(x2);
     display(x5);
     x2 = x5+10;
     x2 = num2str(x2);
elseif y3 > 0
     x5 = str2num(x3);
     display(x5);
     x3 = x5+10;
     x3 = num2str(x3);
elseif y4 > 0
     x5 = str2num(x4);
     display(x5);
     x4 = x5+10;
     x4 = num2str(x4);
else
     x5=0;
end

z = serial('COM3', 'BaudRate', 9600);
fopen(z);
res = strcat('[F',x1,'S',x2,'T',x3,'L',x4,'!]');
pause(5);
display(res);
fprintf(z, res);
fclose(z);    


function n= processing(F,B)
s=imsubtract(F,B);

i=rgb2gray(s);
i=imbinarize(i,0.1);

i=medfilt2(i,[18,18]);
j=imfill(i,'holes');
i=imclose(j,strel('disk',5));
i=logical(i);
vislabels(i)
q=regionprops(i,'AREA','Perimeter','centroid','Extrema', 'BoundingBox');
figure,imshow(F)
hold on
for k = 1:numel(q)
    bb=q(k).BoundingBox;
    rectangle('Position',[bb(1),bb(2),bb(3),bb(4)],'EdgeColor','r','LineWidth',2);
    plot(q(k).Centroid(1),q(k).Centroid(2),'b*');
    
    
end
hold off

n=numel(q);
end

function [t1,t2,t3,t4]= crop(c)
t1 = imcrop(c,[5 162 205 195]);
t2 = imcrop(c,[206 2 200 155]);
t3 = imcrop(c,[405 155 233 191]);
t4 = imcrop(c,[216 354 190 122]);
end


function vislabels(L)
background_shade = 200;
foreground_shade = 240;
I = zeros(size(L), 'uint8');
I(L == 0) = background_shade;
I(L ~= 0) = foreground_shade;
figure()
imageHandle = imshow(I, 'InitialMagnification', 'fit');
axesHandle = ancestor(imageHandle, 'axes');
s = regionprops(L, 'Extrema');
hold(axesHandle, 'on');
for k = 1:numel(s)
   e = s(k).Extrema;
   text(e(1,1), e(1,2), sprintf('%d', k), ...
      'Parent', axesHandle, ...
      'Clipping', 'on', ...
      'Color', 'b', ...
      'FontWeight', 'bold');
end
hold(axesHandle, 'off');
end
