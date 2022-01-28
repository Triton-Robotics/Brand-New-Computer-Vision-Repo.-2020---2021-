# Armor

## <mark style="color:purple;">LED\_bar</mark>

```cpp
explicit LED_bar(const cv::RotatedRect &rect) {
    }
```

## <mark style="color:purple;">Armor</mark>

```cpp
/**
 * TODO
 * @param 
 * @return 
 */
Armor::Armor(const LED_bar &left, const LED_bar &right);
```

```cpp
void Armor::draw_Armor(cv::Mat &image, cv::Point2f roi_offset, bool drawCenter) const;
```



```
 bool Armor::Armor_constraints();
```

```
int Armor::get_average_intensity(const cv::Mat &img);
```





