shader_type spatial;

uniform sampler2DArray icon_array : source_color, filter_nearest;

varying vec4 custom_data;

// Цвета подсветок: 0 = Норма, 1 = Ход (зеленый), 2 = Выбор (желтый), 3 = Атака (красный)
const vec4 HIGHLIGHTS[4] = vec4[4](
    vec4(0.0, 0.0, 0.0, 0.0), 
    vec4(0.0, 1.0, 0.0, 0.5), 
    vec4(1.0, 0.9, 0.0, 0.7), 
    vec4(1.0, 0.0, 0.0, 0.6)  
);

void vertex() {
    custom_data = INSTANCE_CUSTOM;
}

void fragment() {
    float tex_index = custom_data.r;
    int state_id    = clamp(int(custom_data.g), 0, 3);

    // Считываем иконку по UV и индексу слоя
    vec4 tex_color = texture(icon_array, vec3(UV, tex_index));
    vec4 overlay   = HIGHLIGHTS[state_id];

    // Накладываем цвет оверлея поверх текстуры
    ALBEDO = mix(tex_color.rgb, overlay.rgb, overlay.a);
}