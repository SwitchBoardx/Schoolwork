using UnityEngine;
using System.Collections;

public class CameraController : MonoBehaviour
{
    GameObject player;
    float m_smoothX;
    float m_smoothY;
    float m_distanceX;
    float m_distanceY;
    bool playerFacingRight;
    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
        m_smoothX = 0;
        m_smoothY = 0;
        playerFacingRight = true;
    }

    void FixedUpdate()
    {
        CameraFollow();

    }
    void CameraFollow()
    {
        playerFacingRight = player.GetComponent<PlayerController>().m_facingRight;
        

        
        m_distanceY = transform.position.y - player.transform.position.y;
        m_smoothX = 0;
        m_smoothY = 0;
        
        float ySize = Vector3.Distance(Camera.main.ViewportToWorldPoint(new Vector3(0, 0.4515f, 0)), Camera.main.ViewportToWorldPoint(new Vector3(0, 0.4f, 0)));
        if (playerFacingRight)
        {
            Vector3 pointOnScreen = Camera.main.ViewportToWorldPoint(new Vector3(0.35f, 0.0f, -10.0f));
            Vector3 distance = pointOnScreen - player.transform.position;
            m_smoothX = distance.x * 40;
        }
        else
        {
            Vector3 pointOnScreen = Camera.main.ViewportToWorldPoint(new Vector3(0.65f, 0.0f, -10.0f));
            Vector3 distance = pointOnScreen - player.transform.position;
            m_smoothX = distance.x * 25;
        }
        //if (Mathf.Abs(m_distanceX) >= xSize)
        //    m_smoothX = m_distanceX * 15;
        if (Mathf.Abs(m_distanceY) >= ySize)
            m_smoothY = m_distanceY * 100;
        
        transform.GetComponent<Rigidbody2D>().velocity = new Vector3(-m_smoothX, -m_smoothY, 0) * Time.deltaTime;
    }
}
