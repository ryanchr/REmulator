1��ͼ���ɫ��������
clear;
clc;
f=imread('Peppers1.jpg');
h=zeros(256,1);
hs=zeros(256,1);
hp=zeros(256,1);
[m,n]=size(f);                     %ȡ��ͼ�����������
g=zeros(m,n);
for i=1:m
    for j=1:n
        h(f(i,j)+1)=h(f(i,j)+1)+1;     %��¼�Ҷ�ɫ��ֵ
    end
end
Nf=m*n;							%��¼�����ظ���
for i=1:256
    hs(i)=h(i)/Nf;					%���ֱ��ͼ�и�ɫ��ֵ��ռ�ٷֱ�
end
for i=1:256
    hp(i)=sum(hs(1:i));				%�����ۼƷֲ�
end
for i=1:m							%�����ͼ��ĻҶ�ֵ
    for j=1:n
        if f(i,j)==0
            g(i,j)=0;
        else
            g(i,j)=uint8(256*hp(f(i,j)));   
        end
    end
end
subplot(1,2,1);
imshow(f);							%��ʾԭͼ��
subplot(1,2,2);
imshow(uint8(g));					%��ʾɫ�����������ͼ��	

