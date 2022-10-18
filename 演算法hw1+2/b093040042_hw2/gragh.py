import matplotlib.pyplot as plt
import pandas as pd
file_size = 3
for i in range(1,file_size+1):
    with open(f'dt{i}/point.txt','r') as file_point,\
         open(f'ans_dt{i}.txt','r') as file_ans:
        print(f'dt{i}')
        points = {}
        while(line:=file_point.readline()):
            name,x,y = line.split(' ')[0:3]#first 3 words
            points[name]=(int(x),int(y))
        points = pd.DataFrame(points,index=['x','y'])
        print('points')
        print(points)
        ans = [line.strip() for line in file_ans.readlines()][1:]#remove first line
        ans = points[ans+[ans[0]]]#complete the route by adding starting point
        print('answers')
        print(ans)
        x = ans.loc['x']
        y = ans.loc['y']
        names = ans.columns
        plt.plot(x,y)
        for x,y,name in zip(x,y,names):
            plt.annotate(name,(x,y))
        plt.title(f'dt{i}')
        plt.savefig(f'fig{i}.png')
        plt.show()
