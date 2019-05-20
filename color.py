import cv2
import numpy as np
import collections 

# use a dict to record color threshold value 
def getColorList():
    dict = collections.defaultdict(list)
 
    # red
    lower_red = np.array([156, 43, 46])
    upper_red = np.array([180,255,255])
    color_list = []
    color_list.append(lower_red)
    color_list.append(upper_red)
    dict['红灯灭'] = color_list
 
    # orange
    lower_orange = np.array([11, 43, 46])
    upper_orange = np.array([25, 255, 255])
    color_list = []
    color_list.append(lower_orange)
    color_list.append(upper_orange)
    dict['红灯亮'] = color_list

    # green on 
    lower_green = np.array([35, 43, 127])
    upper_green = np.array([77, 255, 255]) 
    color_list = []
    color_list.append(lower_green)
    color_list.append(upper_green) 
    dict['绿灯亮'] = color_list

    # green out 
    lower_green = np.array([35, 43, 46])
    upper_green = np.array([77, 255, 80]) 
    color_list = []
    color_list.append(lower_green)
    color_list.append(upper_green)
    dict['绿灯灭'] = color_list
    return dict

# process the image and estimate the color of switch lamp
def get_color(frame):
    print('go in get_color')
    hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    # cv2.imshow('hsv.jpg',hsv)
    maxsum = -100
    color = None
    color_dict = getColorList()    # get the dict
    for d in color_dict:
        mask = cv2.inRange(hsv,color_dict[d][0],color_dict[d][1])        
        binary = cv2.threshold(mask, 127, 255, cv2.THRESH_BINARY)[1]
        binary = cv2.dilate(binary,None,iterations=2)
        # cv2.imshow(d+'.jpg', binary)
        sum = 0
        height, width = binary.shape 
        for i in range(height): 
            for j in range(width):
                if binary[i,j] == 255:
                    sum += 1
        # print('d',sum)
        # estimate the color from the max of all image colors
        if sum > maxsum :
            maxsum = sum
            color = d     
    return color

if __name__ == '__main__':
    frame = cv2.imread('H:/red2.jpg')  # put you switch lamp image here
    print(get_color(frame))            
    cv2.waitKey(0)
    cv2.destroyAllWindows()