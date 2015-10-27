using UnityEngine;
using System.Collections;

public class PlayerController : MonoBehaviour {


    //Member Variables
    float m_movementSpeed = 0.07f;
    //uint m_health = 100;
    float m_h;
    float m_jumpVelocity;
    float m_jumpDamp = 0.25f;
    bool m_groundedLeft;
    bool m_groundedRight;
    public bool m_facingRight;

    //Objects for checking ground Linecast and rigidbody for player.
    public Transform groundCheckLeft;
    public Transform groundCheckRight;
    Rigidbody2D rbPlayer;

	void Start () 
    {
        
        m_facingRight = true;
        //Get Rigidbody2D Component
        rbPlayer = gameObject.GetComponent<Rigidbody2D>();
	}
	
	void Update () 
    {
        //Horizontal Left-right Input
        m_h = Input.GetAxisRaw("Horizontal");
        //Linecasts left and right sides of player to see if they are grounded.
        m_groundedRight = Physics2D.Linecast(new Vector2(groundCheckRight.position.x, (groundCheckRight.position.y + 1)), (groundCheckRight.position + new Vector3(0, -0.1f, 0)), 1 << LayerMask.NameToLayer("Blocking Layer"));
        m_groundedLeft = Physics2D.Linecast(new Vector2(groundCheckLeft.position.x, (groundCheckLeft.position.y + 1)), (groundCheckLeft.position + new Vector3(0, -0.1f, 0)), 1 << LayerMask.NameToLayer("Blocking Layer"));
        //Jump Input.
        if (Input.GetButtonDown("Jump") && (m_groundedRight || m_groundedLeft))
            Jump();
	}

    void FixedUpdate()
    {
        Move();

        //Jump Code based off own physics because Unity AddForce is wonky.
        Vector2 pos = transform.position;
        if (m_jumpVelocity != 0)
        {
            //Change Y position based on velocity, dampen by m_jumpDamp * deltaTime
            pos.y += m_jumpVelocity;
            m_jumpVelocity -= m_jumpDamp * Time.deltaTime;
            //When Velocity is 0, turn gravity on.
            if (m_jumpVelocity <= 0)
            {
                rbPlayer.gravityScale = 1.0f;
                m_jumpVelocity = 0.0f;
            }
            //Set the position of the player to the calculated position if velocity is <= 0
            transform.position = pos;
        }
        
    }
    void Move()
    {
        //Left-Right movement code
        if (m_h > 0.0f)
        {
            m_facingRight = true;
            gameObject.transform.position = new Vector2(gameObject.transform.position.x + m_movementSpeed, gameObject.transform.position.y);
        }
        else if (m_h < 0.0f)
        {
            m_facingRight = false;
            gameObject.transform.position = new Vector2(gameObject.transform.position.x - m_movementSpeed, gameObject.transform.position.y);
        }
    }
    void Jump()
    {
        //Disable gravity physics on rigidbody2d while jumping for a consistent jump.
        m_jumpVelocity = 0.16f;
        rbPlayer.gravityScale = 0.0f;
    }
}
