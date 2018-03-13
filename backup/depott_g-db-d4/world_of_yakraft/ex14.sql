SELECT quest.title
FROM quest
JOIN character_quests
    ON quest.id = character_quests.quest_id
    JOIN character
        ON character.id = character_quests.character_id
           AND character.name = 'Kuro';
