#include <GL/glew.h>
#include "app.h"
#include "context.h"
#include "shader.h"
#include "quad.h"
#include "texture.h"
#include "video.h"
#include "syphon.h"

int main(void) {
  FirkinApp *app = createApp();
  FirkinContext *ctx = createContext();
  useContext(ctx);

  FirkinShader *sdr = createShader();
  FirkinQuad *quad = createQuad();
  FirkinTexture *tex = createTetxture();
  FirkinVideo *video;
  FirkinSyphonServer *fss = createSyphonServer("Firkin", ctx);
  unsigned char pixels[24] = { 255, 0, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255,
                               0, 0, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255 };
  setTexturePixels(tex, 3, 2, GL_RGBA, pixels);

  useShader(sdr);
  setQuadAttribPointer(quad);
  useTexture(tex, sdr);

  if ((video = loadVideo("/Users/canon/Downloads/awa.mp4")) != NULL) {
    readVideoFrame(video);

    while(shouldContextClose(ctx) == GL_FALSE) {
      if (initContextLoop(ctx) == GL_TRUE) {
        useShader(sdr);
        useTexture(tex, sdr);
        publishSyphonTexture(fss, tex);
        drawQuad(quad);
        finalizeContextLoop(ctx);
      }
    }

    releaseVideo(video);
  }

  terminateSyphonServer(fss);
  terminateTexture(tex);
  terminateQuad(quad);
  terminateContext(ctx);
  terminateApp(app);
  return 0;
}
