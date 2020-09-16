import matplotlib.pyplot as plt
import numpy as np
import argparse

def input_arg():
    '''
    y=wx+b
    '''

    parser = argparse.ArgumentParser(description='fill arguement')

    parser.add_argument('--weight', type=int, required=True,
                        help='the gradient of the line')

    parser.add_argument('--bios', type=int, required=True,
                        help="the bios of the line")

    parser.add_argument('--learn', type=int, required=False, default=1,
                        help="the learning rate of gradient descent")

    args = parser.parse_args()

    w = args.weight
    b = args.bios
    lr = args.learn

    while (True):
        check = input("input q the quit or input else to continue")
        if(check == "q"):
            break
        draw(w, b)
        w, b = gradient_descent(w, b, lr)

def draw(w, b):
    x = np.linspace(-100, 100, 10000)
    y = [i*w+b for i in x]
    
    f = plt.figure(w)
    plt.plot(x, y)
    plt.title("weight: {w} height: {b}".format(w=str(w), b=str(b)),fontsize=12,color='black')
    f.show()
    
    
def gradient_descent(w, b, lr):
        '''
        loss=(wx'+b-y)^2
        gradient= d (wx'+b-y)^2 / dw
        '''
        x = int(input("input new x: "))
        y = int(input("input new y: "))

        loss =  (w*x+b-y)*(w*x+b-y)
        print("loss",loss)
        gradient_w = 2*(w*x+b-y)*x
        gradient_b = (w*x+b-y)
        w = w-gradient_w*lr
        b = b-gradient_b*lr
        print("new wieght :", w)
        print("new bios :", b)
        return w, b

    
if __name__ == "__main__":
    input_arg()

