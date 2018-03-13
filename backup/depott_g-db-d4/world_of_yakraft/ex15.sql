SELECT quest.title, character.name
FROM quest
JOIN character_quests
    ON quest.id = character_quests.quest_id
    JOIN character
        ON character.id = character_quests.character_id
           AND complete = 0;
