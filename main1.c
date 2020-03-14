#include <mlx.h>

int     main(void)
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    int     *img_data;
    int     k;
    int i;
    int j;

    i = 0;
    j = 0;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "kelllati");
    img_ptr = mlx_new_image(mlx_ptr, 1000, 1000);
    img_data = (int *)mlx_get_data_addr(img_ptr, &k, &k, &k);
    while(j < 500)
    {
        i = 0;
        while(i < 500)
        {
            img_data[j * 1000 + i] = 0xffffff * i;
            i++;
        }
        j++;
    }
    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
    mlx_loop(mlx_ptr);
}