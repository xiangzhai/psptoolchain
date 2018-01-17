/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * hello.c - Hello World example App.
 *
 * Copyright (C) 2018 Leslie Zhai <lesliezhai@llvm.org.cn>
 * Copyright (C) 2008 Leslie Zhai <xiang.zhai@cctec.com.cn>
 *
 */

#include <pspdebug.h>
#include <pspkernel.h>

PSP_MODULE_INFO("Hello World", 0, 1, 1);

#define printf pspDebugScreenPrintf

static int setupCallbacks();
static int callbackThread(SceSize args, void *argp);
static int exitCallback(int arg1, int arg2, void *common);

/* Exit callback */
static int exitCallback(int arg1, int arg2, void *common) {
  sceKernelExitGame();
  return 0;
}

/* Callback thread */
static int callbackThread(SceSize args, void *argp) {
  int cbid;

  cbid = sceKernelCreateCallback("Exit Callback", exitCallback, NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();

  return 0;
}

/* Sets up the callback thread and returns its thread id */
static int setupCallbacks() {
  int thid = 0;

  thid =
      sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0, 0);
  if (thid >= 0)
    sceKernelStartThread(thid, 0, 0);

  return thid;
}

int main(int argc, char *argv[]) {
  pspDebugScreenInit();

  setupCallbacks();

  printf("Hello world");

  sceKernelSleepThread();

  return 0;
}
