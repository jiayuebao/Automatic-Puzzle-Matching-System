# Automatic-Puzzle-Matching-System
Implemented an auto-controlled system which could solve and win a puzzle game ***Jigty*** with high speed and success rate.  
The result beat most of the other teams and was chosen as the ***"best team"*** .

| puzzle size        | best time    |  average time  |
| --------   | :-----:   | :----: | 
| 2*2        | 13 sec     |   15~20 sec  |
| 3*3        | 32 sec      |   40~60 sec    |
| 4*4        |  1 min 22 sec     |   2 min 30 sec    |
| 5*5        | 2 min 58 sec      |   4 min    |	
| 6*6        | 14 min 31 sec      |   20 min    |	
| 7*7        | 20 min      |   finish 98%    |	
| 8*8 (highest level)        | --      |   finish 90%    |	
     

## Platform
- opencv 2.4.9+ 
- Qt 5.7 
- FFmpeg 2.2.2
- CyberDip 

## Implementation
 Please check **qtCyberDip::processImg** for a more detailed look of my work.

### Preprocessing
- Jigty installed on smartphone/tablet 
- Adjust the screen size with CyberDip device 

### Step 1: Scan: search the puzzle pieces 
- **Dynamic moving ROI**  
  - ROI height: H * 0.27
  - ROI width: W / n
  - ROI moving step (fast): H / (2n-1)
  - ROI moving step (slow): H / (4n-1)  
  ***(Note: image size is H * W and has n\*n puzzle pieces)*** 
- **Moving pattern** 
	- puzzle size : 2 \* 2 ~ 4 \* 4
  <img src="https://github.com/jiayuebao/Automatic-Puzzle-Matching-System/blob/master/qtCyberDip/pictures/scan4.png" height=50%, width=50%>
	- puzzle size : 5 \* 5 
	- puzzle size : 6 \* 6 ~ 8 \* 8	 
    
    

### Step 2: Match 
- **Feature Detection**
  - SURF detector
  ```
    SurfFeatureDetector detector(value);
    SurfDescriptorExtractor extractor;
    
    // detect surf feature
	detector.detect(img_1, keypoints1);
	detector.detect(img_2, keypoints2);
    
    // calculate surf descriptors
    Mat descriptors1, descriptors2;
	extractor.compute(img_1, keypoints1, descriptors1);
	extractor.compute(img_2, keypoints2, descriptors2);
  ```
- **Matchers**
  - BFMatch
  - KnnMatch (k = 2)
  ```
  BruteForceMatcher<L2<float>>matcher;
  
  vector<vector<DMatch>>matches1;
  vector<vector<DMatch>>matches2;
  
  // img1 -> img2, img2 -> img1 knn(k = 2)
  matcher.knnMatch(descriptors1, descriptors2, matches1, 2);
  matcher.knnMatch(descriptors2, descriptors1, matches2, 2);
  ```
- **Ratio Testing**
	- remove unreliable matches
	```
    float ratio = 0.65f;
    
    if ((optimal match/suboptimal match) > ratio) remove;
    else keep;
    ```
- **Symmetric Testing**
  -  make sure the match points for two images are the same
 
### Step 3: Drag 
- matching point to matching point 
  - find the matching position on the original image and the puzzle piece 
  - calculate the moving direction and distance
- interaction with the hardware
  - comMoveToScale()
  - comHitDown()
  - comHitUp()

## Limitations
-  
