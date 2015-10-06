using UnityEngine;
using System.Collections;

public class PlayerController : MonoBehaviour {

    float m_movementSpeed;
    int m_health;
    float m_h;
    void Move()
    {
        
        m_h = Input.GetAxis("Horizontal");
        if (m_h > 0.0f)
            gameObject.transform.position = new Vector2(gameObject.transform.position.x + m_movementSpeed, gameObject.transform.position.y);
        else if (m_h < 0.0f)
            gameObject.transform.position = new Vector2(gameObject.transform.position.x - m_movementSpeed, gameObject.transform.position.y);
    }

	void Start () 
    {
        m_movementSpeed = 0.02f;
        m_health = 100;
	}
	
	// Update is called once per frame
	void Update () 
    {
        Move();
	}
}
