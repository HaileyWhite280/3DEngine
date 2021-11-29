// fragment
    #version 430 core
    in vec3 fs_color;
    in vec2 fs_texcoord;

    out vec4 outColor;

    uniform vec3 tint;
    uniform sampler2D tSampler;

    void main()
    {
      //outColor = vec4(fs_color, 1.0) * vec4(tint, 1.0) * texture(tSampler, fs_texcoord);
      outColor = texture(tSampler, fs_texcoord);
    }