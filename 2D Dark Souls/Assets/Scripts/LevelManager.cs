using UnityEngine;
using System.Collections;

public class LevelManager : MonoBehaviour {

    public GameObject FloorPrefab;
    private GameObject[] floorTiles;
    Vector2 m_tileSize;
    Vector2 m_screenTiles;

	// Use this for initialization
	void Start () 
    {
        
        m_tileSize.y = FloorPrefab.GetComponent<SpriteRenderer>().bounds.size.y;
        m_tileSize.x = FloorPrefab.GetComponent<SpriteRenderer>().bounds.size.x;

        m_screenTiles.x = m_tileSize.x / Screen.width;
        m_screenTiles.y = Screen.height / m_tileSize.y;
        
        FloorPrefab = Instantiate(FloorPrefab, new Vector3(-10.0f + (m_tileSize.x * 0.5f), -(m_tileSize.y * 0.5f), 0.0f), FloorPrefab.transform.rotation) as GameObject;
        
	}
	
	// Update is called once per frame
	void Update () 
    {
	
	}
}
