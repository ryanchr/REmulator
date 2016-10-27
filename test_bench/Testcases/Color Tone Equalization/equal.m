1、图像的色调均化。
clear;
clc;
f=imread('Peppers1.jpg');
h=zeros(256,1);
hs=zeros(256,1);
hp=zeros(256,1);
[m,n]=size(f);                     %取得图像的行与列数
g=zeros(m,n);
for i=1:m
    for j=1:n
        h(f(i,j)+1)=h(f(i,j)+1)+1;     %记录灰度色调值
    end
end
Nf=m*n;							%记录总像素个数
for i=1:256
    hs(i)=h(i)/Nf;					%求出直方图中各色调值所占百分比
end
for i=1:256
    hp(i)=sum(hs(1:i));				%计算累计分布
end
for i=1:m							%求出新图像的灰度值
    for j=1:n
        if f(i,j)==0
            g(i,j)=0;
        else
            g(i,j)=uint8(256*hp(f(i,j)));   
        end
    end
end
subplot(1,2,1);
imshow(f);							%显示原图像
subplot(1,2,2);
imshow(uint8(g));					%显示色调均化后的新图像	

