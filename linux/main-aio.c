    }

    L("bzImage",            &kernel,  &kernel_size,  1);
    L("initramfs.cpio.gz",  &initrd,  &initrd_size,  1);
    L("bootargs.txt",       &cmdline, &cmdline_size,  0);

    if (cmdline && cmdline_size) {
        for (int i = 0; i < (int)cmdline_size; i++)
            if (cmdline[i] == '\n') { cmdline[i] = '\0'; break; }
    } else {
        cmdline = "panic=0 clocksource=tsc consoleblank=0 net.ifnames=0 "
                  "radeon.dpm=0 amdgpu.dpm=0 drm.debug=0 "
                  "console=ttyS0,115200n8 console=tty0 "
                  "video=HDMI-A-1:1360x768@60";
    }

    L("vram.txt", &vramstr, &vramstr_size, 0);
    if (vramstr && vramstr_size) {
        vram_mb = my_atoi(vramstr);
        if (vram_mb < VRAM_MB_MIN || vram_mb > VRAM_MB_MAX)
            vram_mb = VRAM_MB_DEFAULT;
    } else {
        vram_mb = VRAM_MB_DEFAULT;
    }

    // Launch kernel exploit → kernel_main()