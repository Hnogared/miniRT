/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnogared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 22:04:31 by hnogared          #+#    #+#             */
/*   Updated: 2024/01/06 22:15:44 by hnogared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

/* image_handling.c */
t_image			my_new_image(void *mlx_ptr, int width, int height);
size_t			get_image_pixel(t_image image, int x, int y);
void			set_image_pixel(t_image *image, int x, int y, size_t color);

/* render_window.c */
int				open_render_window(t_data *data, char *title);
int				redraw_render_window(t_data *data);

/* rgb_color.c */
int				ft_min(int num1, int num2);
size_t			rgb_to_sizet(t_rgb_color color);
size_t			sizet_color_mix(size_t color1, size_t color2, float ratio);
t_rgb_color		rgb_color_lighten(t_rgb_color start_color,
					t_rgb_color add_color, float ratio);
t_rgb_color		rgb_color_mix(t_rgb_color start_color, t_rgb_color mix_color,
					float ratio);

/* window_handling.c */
size_t			get_window_pixel(t_window window, int x, int y);
size_t			get_window_virtual_pixel(t_window window, int x, int y);
t_window		my_new_window(void *mlx_ptr, int dimensions[2], int pixel_ratio,
					char *title);
void			my_destroy_window(void *mlx_ptr, t_window *window);
void			redraw_window(void *mlx_ptr, t_window *window);

/* window_modification.c */
t_window		*set_window_pixel_ratio(t_window *to_modify, int pixel_ratio);
void			set_window_pixel(t_window *window, int x, int y, size_t color);
void			set_window_virtual_pixel(t_window *window, int x, int y,
					size_t color);
void			put_square_to_window(t_window *window, int start_coords[2],
					int size[2], size_t color);
void			put_percent_to_window(t_xvar *mlx_ptr, t_window window,
					int percentage, int color);

#endif
