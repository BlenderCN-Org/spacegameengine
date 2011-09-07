__kernel void hello_kernel(
	write_only image2d_t input_image)
{
	size_t x = get_global_id(0);
	size_t y = get_global_id(1);
	write_imagef(
		input_image,
		(int2)(
			x,
			y),
		(float4)(
			1.0f,
			1.0f,
			1.0f,
			1.0f));
}
