import numpy as np  
import matplotlib.pyplot as plt

w = np.random.rand(1)
b = np.random.rand(1)

x = np.random.rand(100)
y = 2 * x + 7

epoch = 1000
lr = 0.001

def loss(w, b, x, y):
    loss = 0
    for i, j in zip(w, b):
        loss += np.sqrt((w*i+b-j)**2)
    return loss/len(x)



def train(w, b, x, y, epoch, lr):
    print("intitial loss", loss(w,b ,x, y))
    for i in range(epoch):
        #question 2 ?
        dl_dw = np.sum((w*x+b-y)*x) / len(x)
        dl_db = np.sum(w*x+b-y) / len(x)
        w = w - dl_dw*lr
        b = b - dl_db*lr
        print("{i}-th loss:",loss(w, b, x, y))
    return w, b

    
if __name__ == "__main__":
    f = plt.figure()
    plt.plot(x, y)
    plt.title("initial line to train")
    f.show()

    w, b = train(w, b, x, y , epoch, lr)
    print(w, b)
    c  = plt.figure()
    plt.plot(w*x+b, y)
    plt.title("training line")
    c.show()
    while(True):
        q = input("input q to quick")
        if(q == 'q'):
            break

    