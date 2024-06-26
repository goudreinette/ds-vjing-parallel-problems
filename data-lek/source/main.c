#include <nds.h>
#include <stdio.h>
#include <NEMain.h>
#include <math.h>



// First you have to put the .bin files in the data folder. This will generate
// (after doing "make") some files named "binfilename_bin.h". For example,
// "model.bin" will generate a file named "model_bin.h". You have to include
// this in "main.c".
//
// The name you will have to use is "binfilename_bin". For example, for loading
// "model.bin" you will have to use:
//
//     NE_ModelLoadStaticMesh(Model, binfilename_bin);
//


#include "biertje_bin.h"
#include "biertjetex.h"



typedef struct {
    NE_Camera *camera;
    NE_Model *angel;
    int polyId;
} SceneData;

void Draw3DScene(void *arg)
{
    SceneData *scene = arg;

    NE_CameraUse(scene->camera);
    // Set polygon format
    // NE_PolyFormat(31, scene->polyId, NE_LIGHT_0, NE_CULL_BACK, NE_TOON_HIGHLIGHT_SHADING);
    // NE_PolyFormat(31, scene->polyId, NE_LIGHT_0, NE_CULL_BACK, 0);
    
    NE_ModelDraw(scene->angel);
}


int main(int argc, char *argv[])
{
    SceneData scene = { 0 };
    scene.polyId = 0;

    irqEnable(IRQ_HBLANK);
    irqSet(IRQ_VBLANK, NE_VBLFunc);
    irqSet(IRQ_HBLANK, NE_HBLFunc);

    // Init Nitro Engine in normal 3D mode
    NE_Init3D();

    // libnds uses VRAM_C for the text console, reserve A and B only
    NE_TextureSystemReset(0, 0, NE_VRAM_AB);
    // Init console in non-3D screen
    consoleDemoInit();

    // Allocate space for the objects we'll use
    scene.angel = NE_ModelCreate(NE_Static);
    scene.camera = NE_CameraCreate();
    NE_Material *material = NE_MaterialCreate();


    // Set coordinates for the camera
    NE_CameraSet(scene.camera,
                 -10, 3, 0,  // Position
                  0, 3, 0,  // Look at
                  0, 1, 0); // Up direction

    // Load mesh from RAM and assign it to the object "Model".
    NE_ModelLoadStaticMesh(scene.angel, biertje_bin);
    // Load a RGB texture from RAM and assign it to "Material".
    NE_MaterialTexLoad(material, NE_RGB5, 256, 256, NE_TEXGEN_TEXCOORD,
                       biertjetexBitmap);

    // Assign texture to model...
    NE_ModelSetMaterial(scene.angel, material);

        // Set some properties to the material
    NE_MaterialSetProperties(material,
                  RGB15(31, 31, 31), // Diffuse
                  RGB15(16, 16, 16), // Ambient
                  RGB15(31, 31, 31),    // Specular
                  RGB15(0, 0, 0),    // Emission
                  false, false);     // Vertex color, use shininess table


    // We set up a light and its color
    NE_LightSet(0, NE_White, -1, -1, -0.5);
    // NE_LightSet(2, NE_White, -1, -3, -0.5);

    // NE_ClearColorSet(RGB8(69,40,60), 31, 63);
    NE_ClearColorSet(RGB8(34,32,52), 31, 63);
    setBackdropColorSub(RGB8(34,32,52));
    

    // This enables shading (you can choose normal or toon).
    // NE_SetupToonShadingTables(true);    
    // This enables outlining in all polygons, so be careful
    NE_OutliningEnable(true);
    // We set the second outlining color to red.
    // This will be used by polygons with ID 8 - 15.
    NE_OutliningSetColor(scene.polyId, NE_Black);



    // NFLib setup the background
    // NF_Set2D(0, 0);
    // NF_SetRootFolder("NITROFS");

    // NF_InitTiledBgBuffers();    // Initialize storage buffers
    // NF_InitTiledBgSys(0);       // Top screen

    // // Load background files from NitroFS
    // NF_LoadTiledBg("bg", "bg", 512, 512);

    // // Create top screen backgrounds
    // NF_CreateTiledBg(0, 0, "bg");




    double t;

    while (1)
    {
        t++;

        // Wait for next frame
        NE_WaitForVBL(0);

        // Get keys information
        scanKeys();
        uint32_t keys = keysHeld();

        printf("\x1b[1;1HPad: Rotate.");


        NE_ModelRotate(scene.angel, 0,-1,0);

        NE_ModelSetCoord(scene.angel, 0, sinf(t / 30) * 1.2, 0);

        // Spinnnn
        // if (keys & KEY_UP) {
        //     NE_ModelRotate(scene.angel, 0,0,-1);
        // }
        // if (keys & KEY_DOWN) {
        //     NE_ModelRotate(scene.angel, 0,0,1);
        // }   
        // if (keys & KEY_LEFT) {
        //     NE_ModelRotate(scene.angel, 0,1,0);
        // }
        // if (keys & KEY_RIGHT) {
        //     NE_ModelRotate(scene.angel, 0,-1,0);
        //     // NE_ModelSetCoord
        // }

        //NE_ModelRotate(scene.angel, 0, 0, -1);
        // NE_ModelRotate(scene.dsModelBottom, 0, 1, 0);
        
        printf("\x1b[2;1HZ: %i", scene.angel->rz);
        
        // Draw scene
        NE_ProcessArg(Draw3DScene, &scene);
    }

    return 0;
}
