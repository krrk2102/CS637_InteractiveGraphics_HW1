// First new GL program
// Makes a red triangle, a quadrilateral and a pentagon

#include "Angel.h"

const int NumPoints = 3;

//--------------------------------------------------------------------------

void
init( void )
{
    // Specify the vertices for a triangle. 
    vec2 tri[3] = {
        vec2( -0.8, -0.8 ), vec2( -0.5, -0.2 ), vec2( -0.2, -0.8 )
    };
    std::cout<<"Vertices for triangle generated."<<std::endl;
    // Specify the vertices for a quadrilateral, in a way of 2 triangles adjacent to each other. 
    vec2 quad[2][3] = {
        vec2( 0.9, -0.8 ), vec2( 0.3, -0.8 ), vec2( 0.2, -0.2 ), 
        vec2( 0.2, -0.2 ), vec2( 0.8, -0.2 ), vec2( 0.9, -0.8 )
    };
    std::cout<<"Vertices for quadrilateral generated."<<std::endl;
    // Specify the vertices for a pentagon, in a way of 5 triangles connected in the center point. 
    vec2 penta[5][3] = {
        vec2( 0, 0.5 ), vec2( 0, 0.8 ), vec2( 0.6, 0.6 ),
        vec2( 0, 0.5 ), vec2( 0, 0.8 ), vec2( -0.6, 0.6 ),
        vec2( 0, 0.5 ), vec2( 0.4, 0.2 ), vec2( 0.6, 0.6 ),
        vec2( 0, 0.5 ), vec2( -0.4, 0.2 ), vec2( -0.6, 0.6 ),
        vec2( 0, 0.5 ), vec2( 0.4, 0.2 ), vec2( -0.4, 0.2 )
    };
    std::cout<<"Vertices for pentagon generated."<<std::endl;

    // Create a vertex array object
    GLuint vao[1];
    glGenVertexArrays( 1, vao );
    glBindVertexArray( vao[0] );
    std::cout<<"Vertex array object created and binded."<<std::endl;

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    std::cout<<"Buffer object created and binded."<<std::endl;
    // Assign data to buffer object, the single triangle first, meanwhile reserve the space needed by quadrilateral and pentagon. 
    glBufferData( GL_ARRAY_BUFFER, sizeof(tri) + sizeof(quad) + sizeof(penta), tri, GL_STATIC_DRAW );
    std::cout<<"Data of triangle has been written in buffer."<<std::endl;
    // Add data of quadrilateral to buffer object. 
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(tri), sizeof(quad), quad);
    std::cout<<"Data of quadrilateral has been appended to the buffer."<<std::endl;
    // Add data of pentagon to buffer object. 
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(tri) + sizeof(quad), sizeof(penta), penta);
    std::cout<<"Data of pentagon has been appended to the buffer."<<std::endl;

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );
    std::cout<<"Shaders and shader program loaded."<<std::endl;

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );
    std::cout<<"Vertex position attributes initialized."<<std::endl;

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}

//----------------------------------------------------------------------------

void
display( void )
{
    std::cout<<"Prepare to draw polygons."<<std::endl;
    glClear( GL_COLOR_BUFFER_BIT );     // clear the window
    glDrawArrays( GL_TRIANGLES, 0, 8*NumPoints );    // draw the points
    glFlush();
    std::cout<<"glDrawing finished."<<std::endl;
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
    case 033:
        exit( EXIT_SUCCESS );
        break;
    }
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 512, 512 );
    std::cout<<"glut initialized."<<std::endl;

    glutCreateWindow( "ICG_hw1" );
    glewExperimental=GL_TRUE; 
    glewInit();
    std::cout<<"glew initialized."<<std::endl;
    init();
    std::cout<<"init() executed."<<std::endl;

    glutDisplayFunc( display );
    std::cout<<"Function of display loaded."<<std::endl;
    glutKeyboardFunc( keyboard );
    std::cout<<"Function for keyboard event loaded."<<std::endl;

    std::cout<<"Start glutMianLoop()."<<std::endl;
    glutMainLoop();
    return 0;
}
